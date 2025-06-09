#!/bin/bash

TEXTOS=(textos/*.txt)
REPETICIONES=15
OUTPUT="resultados.csv"
MAIN="experimentos.cpp"
TIMEOUT_LIMIT=40  # segundos

declare -A ALG_NAMES
ALG_NAMES[1]="editDistanceRecursive"
ALG_NAMES[2]="editDistanceMemo"
ALG_NAMES[3]="editDistanceDP"
ALG_NAMES[4]="editDistanceDPOptimized"

normalize_decimal() {
    local val="$1"
    if [[ "$val" =~ ^\.[0-9]+$ ]]; then
        echo "0$val"
    else
        echo "$val"
    fi
}

echo "Algoritmo,Size_texto_A(bytes),Size_texto_B(bytes),Size_avg(bytes),Tiempo_Medio(ns),Stdev,Mem_Peak(KB)" > $OUTPUT

for (( i=0; i<${#TEXTOS[@]}; i++ )); do
    for (( j=0; j<${#TEXTOS[@]}; j++ )); do
        if [ $i -eq $j ]; then continue; fi

        FILE_A="${TEXTOS[$i]}"
        FILE_B="${TEXTOS[$j]}"

        SIZE_A=$(stat -c%s "$FILE_A")
        SIZE_B=$(stat -c%s "$FILE_B")
        MEM_PROM=$(( (SIZE_A + SIZE_B) / 2 ))

        for ALGO in 1 2 3 4; do
            EXECUTABLE="main_algo$ALGO"
            ALGO_NAME="${ALG_NAMES[$ALGO]}"

            g++ -O2 -std=c++17 -DALGO=$ALGO "$MAIN" -o "$EXECUTABLE"
            if [ $? -ne 0 ]; then
                echo "❌ Error compilando ALGO=$ALGO"
                continue
            fi

            tiempos=()
            peaks=()
            ejecuciones_exitosas=0

            for (( r=0; r<$REPETICIONES; r++ )); do
                start_time=$(date +%s%N)

                # Ejecutar con timeout y medir memoria
                /usr/bin/timeout ${TIMEOUT_LIMIT}s /usr/bin/time -f "%M" "./$EXECUTABLE" "$FILE_A" "$FILE_B" 2> temp_mem.txt
                exit_code=$?

                end_time=$(date +%s%N)
                elapsed_ns=$((end_time - start_time))
                elapsed_ns=$(echo "$elapsed_ns / 1000000" | bc -l)

                if [ "$exit_code" -eq 124 ]; then
                    echo "⚠️ Timeout alcanzado para $ALGO_NAME entre $FILE_A y $FILE_B"
                    elapsed_ns=-1
                    mem=-1
                else
                    mem=$(cat temp_mem.txt)
                fi

                echo "Ejecutando algoritmo: $ALGO_NAME con textos: $FILE_A y $FILE_B"
                echo "Tiempo: $elapsed_ns ns"
                echo "Memoria: $mem KB"

                if (( $(echo "$elapsed_ns >= 0" | bc -l) )) && [[ "$mem" =~ ^[0-9]+$ ]]; then
                    tiempos+=($elapsed_ns)
                    peaks+=($mem)
                    ((ejecuciones_exitosas++))
                fi
            done

            if [ "$ejecuciones_exitosas" -eq 0 ]; then
                mean_fmt=-1
                stdev_fmt=-1
                peak_max=-1
            else
                # Calcular promedio
                sum=0
                for t in "${tiempos[@]}"; do
                    sum=$(echo "$sum + $t" | bc -l)
                done
                mean=$(echo "$sum / $ejecuciones_exitosas" | bc -l)

                # Calcular desviación estándar
                sq_diff=0
                for t in "${tiempos[@]}"; do
                    diff=$(echo "$t - $mean" | bc -l)
                    sq=$(echo "$diff * $diff" | bc -l)
                    sq_diff=$(echo "$sq_diff + $sq" | bc -l)
                done

                if [ "$ejecuciones_exitosas" -gt 1 ]; then
                    stdev=$(echo "scale=4; sqrt($sq_diff / ($ejecuciones_exitosas - 1))" | bc -l)
                else
                    stdev=0
                fi

                mean=$(normalize_decimal "$mean")
                stdev=$(normalize_decimal "$stdev")

                mean_fmt=$(LC_NUMERIC=C printf "%.4f" "$mean")
                stdev_fmt=$(LC_NUMERIC=C printf "%.4f" "$stdev")

                # Máxima memoria
                peak_max=0
                for m in "${peaks[@]}"; do
                    if [ "$m" -gt "$peak_max" ]; then
                        peak_max=$m
                    fi
                done
            fi

            echo "$ALGO_NAME,$SIZE_A,$SIZE_B,$MEM_PROM,$mean_fmt,$stdev_fmt,$peak_max" >> $OUTPUT
            rm -f "$EXECUTABLE" temp_mem.txt
        done
    done
done
