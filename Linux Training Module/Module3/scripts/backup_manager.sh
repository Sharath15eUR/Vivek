#!/bin/bash

if [ $# -ne 3 ];then
	echo "Usage: $0 <source_directory> <backup_directory> <file_extension>"
	exit 1
fi

SOURCE_DIR="$1"
BACKUP_DIR="$2"
EXTENSION="$3"

if [ ! -d "$SOURCE_DIR" ]; then
	echo "Error: Source directory does not exist!"
	exit 1
fi

if [ ! -d "$BACKUP_DIR" ]; then
	mkdir -p "$BACKUP_DIR" || {echo "Error: Failed to create a backup Directory"; exit 1;
fi

FILES=("$SOURCE_DIR"/*"$EXTENSION")
if [ ! -e "${FILES[0]}" ]; then
	echo "No files found with the extension in $EXTENSION in $SOURCE_DIR"
	exit 1
fi

export BACKUP_COUNT=0
TOTAL_SIZE=0

for FILE in "${FILES[@]}"; do
	FILE_NAME=$(basename "$FILE")
	FILE_SIZE=$(stat -c%s "$FILE")

	echo "Processing: $FILE_NAME ($FILE_SIZE bytes)"

	DEST_FILE="$BACKUP_DIR/$FILE_NAME"

	if [ -e "$DEST_FILE" ]; then 
		if [ "$FILE" -nt "$DEST_FILE" ]; then
			cp "$FILE" "$DEST_FILE"
			echo "Updated : $FILE_NAME"
		else
			echo "Skipped : $FILE_NAME (Already Upto Date)"
			continue
		fi
	else
		cp "$FILE" "$DEST_FILE"
		echo "Copied : $FILE_NAME"
	fi

	((BACKUP_COUNT++))
	TOTAL_SIZE=$((TOTAL_SIZE+FILE_SIZE))
done

REPORT_FILE="$BACKUP_DIR/backup_report.log"
echo "Backup Report" > "$REPORT_FILE"
echo "Total files backed up : $BACKUP_COUNT" >> "$REPORT_FILE"
echo "Total size of files : $TOTAL_SIZE bytes" >> "$REPORT_FILE"
echo "Backup stored in : $BACKUP_DIR" >> "$REPORT_FILE"

echo "Backup Completed. Report saved to $REPORT_FILE"
