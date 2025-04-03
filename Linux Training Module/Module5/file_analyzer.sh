#!/bin/bash

LOG_FILE="errors.log"

search_directory() {
    local dir=$1
    local keyword=$2

    if [[ ! -d "$dir" ]]; then
        echo "Error: Directory '$dir' not found" | tee -a "$LOG_FILE"
        exit 1
    fi

    grep -rl "$keyword" "$dir" || echo "No matches found."
}

search_file() {
    local file=$1
    local keyword=$2

    if [[ ! -f "$file" ]]; then
        echo "Error: File '$file' not found" | tee -a "$LOG_FILE"
        exit 1
    fi

    grep --color=auto "$keyword" "$file" || echo "No matches found."
}

display_help() {
    cat << EOF
Usage: file_analyzer.sh [OPTIONS]
Options:
  -d <directory>   Search for files in a directory containing the keyword
  -f <file>        Search for a keyword in a specific file
  -k <keyword>     Keyword to search
  --help           Display this help menu

Examples:
  ./file_analyzer.sh -d logs -k error
  ./file_analyzer.sh -f script.sh -k TODO
EOF
}

validate_input() {
    local input=$1
    if [[ -z "$input" ]]; then
        echo "Error: Invalid input. Keyword cannot be empty." | tee -a "$LOG_FILE"
        exit 1
    fi
}

while getopts "d:f:k:-:" opt; do
    case "${opt}" in
        d) DIRECTORY=${OPTARG} ;;
        f) FILE=${OPTARG} ;;
        k) KEYWORD=${OPTARG} ;;
        -)
            case "${OPTARG}" in
                help) display_help; exit 0 ;;
                *) echo "Invalid option: --$OPTARG" | tee -a "$LOG_FILE"; exit 1 ;;
            esac
            ;;
        *) display_help; exit 1 ;;
    esac
done

if [[ -z "$KEYWORD" ]]; then
    echo "Error: Keyword is required" | tee -a "$LOG_FILE"
    display_help
    exit 1
fi

if [[ -n "$DIRECTORY" ]]; then
    search_directory "$DIRECTORY" "$KEYWORD"
elif [[ -n "$FILE" ]]; then
    search_file "$FILE" "$KEYWORD"
else
    echo "Error: Either a directory or a file must be specified" | tee -a "$LOG_FILE"
    display_help
    exit 1
fi
