PID=$(pgrep chip8)

# If a process ID was found, kill it
if [ -n "$PID" ]; then
    echo "Killing running chip8 process (PID: $PID)..."
    kill -9 $PID
else
    echo "No running chip8 process found."
fi
