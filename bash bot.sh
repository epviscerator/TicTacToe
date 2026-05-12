 if [[ "$msg" == *"Turn:X"* ]]; then
        BOT_MOVED=false
        echo "PUNY HUMAN TURN"
    fi

    if [[ "$CURRENT_MODE" == "1P" ]] && [[ "$msg" == *"Turn:O"* ]] && [ "$BOT_MOVED" = false ]; then
        available=""
        for i in {0..8}; do
            char="${current_board:$i:1}"
            if [[ "$char" == " " ]] || [[ -z "$char" ]]; then
                available+="$i "
            fi
        done

        random_move=$(echo $available | xargs -n1 | shuf -n1)

        if [[ -n "$random_move" ]]; then
            BOT_MOVED=true
            echo "Bot moving to: $random_move"
            msg=""
            sleep 1
            mosquitto_pub -h $BROKER -t "tictactoe/move" -m "$random_move"
        fi
    fi
done