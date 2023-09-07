echo scripts start

echo compile all files with g++ and output executables
g++ -o RUN BballRoster.cpp main.cpp -std=c++17

echo Run the file
./RUN

echo remove executable
rm RUN

echo scripts terminated