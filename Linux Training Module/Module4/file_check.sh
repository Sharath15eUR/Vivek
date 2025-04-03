#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 <input_file>"
	exit 1
fi

INPUT_FILE="$1"
OUTPUT_FILE="output.txt"

if [ ! -f "$INPUT_FILE" ]; then
	echo "Error: Input file does not exist"
	exit 1
fi

> "$OUTPUT_FILE"

while IFS= read -r line; do
	frame_time=$(echo "$line" | grep -o '"frame.time": "[^"]*"' | sed -E 's/"fram.time":(.*)/\1/')
	wlan_fc_type=$(echo "$line" | grep -o '"wlan.fc.type": "[^"]*"' | sed -E 's/"wlan.fc.type":(.*)/\1/')
	wlan_fc_subtype=$(echo "$line" | grep -o '"wlan.fc.subtype": "[^"]*"' | sed -E 's/"wlan.fc.subtype":(.*)/\1/')

	if [[ -n "$frame_time" || -n "$wlan_fc_type" || -n "$wlan_fc_subtype" ]]; then
		[[ -n "$frame_time" ]] && echo "\"frame.time\":$frame_time" >> "$OUTPUT_FILE"
		[[ -n "$wlan_fc_type" ]] && echo "\"wlan.fc.type\":$wlan_fc_type" >> "$OUTPUT_FILE"
		[[ -n "$wlan_fc_subtype" ]] && echo "\"wlan.fc.subtype\":$wlan_fc_subtype" >> "$OUTPUT_FILE"
	fi
done < "$INPUT_FILE"

echo "Extraction completed. Output saved in $OUTPUT_FILE"
