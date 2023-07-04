# aws_test
Test for aws sdk C++ bug saving files from Aws::StringStream

## How to run:

- Inside the project directory:
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="[path to vcpkg]/vcpkg/scripts/buildsystems/vcpkg.cmake" ..
```

- docker image command (download and run on port 9000):

```bash
docker run -p 9000:9000 --name minio  -e "MINIO_ACCESS_KEY=minioadmin" -e "MINIO_SECRET_KEY=miniokey" -v C:/aws/data:/data  minio/minio server /data
```
Now data should be mapped into local directory `C:/aws/data`
