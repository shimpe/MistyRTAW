mkdir testoutput
python3.2 /home/shimpe/development/python3/youneedtests/main.py --srcfolder . --recursive --exclude-folder testoutput --outputfolder testoutput --language cpp --generator googletest
cd testoutput
cmake .
make
make test

