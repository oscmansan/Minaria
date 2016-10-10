cd $(dirname $0)

cd OALWrapper
cmake .
make
cd ..
cmake .
make
