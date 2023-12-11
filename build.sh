#!/bin/bash

SCRIPT_NAME=$(basename "$0")
BUILD_DIR="build"
SRC_DIR="src"
APP_NAME="app"
GCC_OPTIONS="-Wall -Wextra -I $SRC_DIR -Wno-unused-parameter -Wno-unused-but-set-variable"
GREEN='\033[0;32m'
RESET='\033[0m'

# Display functions
function show_success {
    tput setaf 2
    echo "✔ $1"
    tput sgr0
}

function show_error {
    tput setaf 1
    echo "✖ Error: $1"
    tput sgr0
}

function show_command {
    tput setaf 3
    echo -e "\t$1"
    tput sgr0
}

# Display arrows
function show_arrows_jump {
    for _ in {1}; do
        echo -e "\n\t⬇  ⬇  ⬇ \n"
        sleep 0.3
    done
}

# Check and create directories
if [ ! -d "$BUILD_DIR" ] && [ "$#" -gt 0 ] && [ "$1" != "--help" ]; then
    mkdir "$BUILD_DIR" || show_error "Unable to create directory $BUILD_DIR."
fi

# Clean
function clean {
    local command="rm -r $BUILD_DIR $APP_NAME"
    echo -e "➔ Cleaning..."
    show_command "$command"
    make clean > /dev/null || show_error "Error during cleaning."
    show_success "Cleaning completed."
}

# Build
function build {
    local command="make"
    echo -e "➔ Building..."
    show_command "$command"
    make > /dev/null || show_error "Error during compilation."
    show_success "Compilation completed."
}

# Execute
function execute {
    local executable="$APP_NAME"
    local command="./$executable"
    echo -e "➔ Executing the executable..."
    show_command "$command"
    if [ -x "$executable" ]; then
        show_arrows_jump
        "$command" || show_error "Error during execution."
    else
        show_error "Error during execution. The file $executable is not executable."
    fi
}

# --help
function show_help {
    echo "Usage: $SCRIPT_NAME [options]"
    echo "Options:"
    echo -e "\t-rbuild, -rb  : \t➔ Clean before rebuilding and execute (alternative)"
    echo -e "\t-debug, -d    : \t➔ Configure compilation in debug mode"
    echo -e "\t-run, -r      : \t➔ Execute the generated executable"
    echo -e "\t-build, -b    : \t➔ Only compile (no cleaning or execution)"
    echo -e "\t-clean, -c    : \t➔ Clean before rebuilding and execute"
    echo -e "\t-docs         : \t➔ Generate Doxygen documentation"
    echo -e "\t--help, -h    : \t➔ Display help"
}

function generate_docs {
    echo -e "➔ Generating Doxygen documentation..."
    show_command "make -B docs"
    make -B docs
    show_success "Documentation generated."
}

# Options loop
while [ "$#" -gt 0 ]; do
    case "$1" in
        -clean | -c)
            clean
            shift
            ;;
        -debug | -d)
            echo -e "➔ Configuring compilation in debug mode..."
            show_command "make debug"
            make debug || show_error "Error configuring in debug mode."
            build
            execute
            shift
            ;;
        -run | -r)
            build
            execute
            shift
            ;;
        -rbuild | -rb)
            clean
            build
            execute
            shift
            ;;
        -build | -b)
            build
            shift
            ;;
        -docs)
            generate_docs
            shift
            ;;
        --help | -h)
            show_help
            exit 0
            ;;
        *)
            show_error "Unrecognized option: $1. Use --help to display help."
            shift
            ;;
    esac
    shift
done
