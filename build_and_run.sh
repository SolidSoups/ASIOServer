#!/bin/bash

set -e

echo "🔨 Building project..."
./build.sh
echo

echo "🏎️ Running executable..."
./run.sh
echo
