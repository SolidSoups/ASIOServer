#!/bin/bash

# Build the project
./build.sh
if [ $? -ne 0 ]; then
    echo "❌ Build failed!"
    exit 1
fi

echo "✅ Build successful, starting NetServerTest..."
./run.sh 