$env:VCPKG_ROOT = "..\..\vcpkg"
$env:PATH = "$env:VCPKG_ROOT;$env:PATH"
$PROTO_FILE = "hello.proto"
& "$env:VCPKG_ROOT\packages\protobuf_x64-windows\tools\protobuf\protoc.exe" --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc="$env:VCPKG_ROOT\packages\grpc_x64-windows\tools\grpc\grpc_cpp_plugin.exe" "$PROTO_FILE"
