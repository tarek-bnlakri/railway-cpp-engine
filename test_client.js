const grpc = require('@grpc/grpc-js');
const protoLoader = require('@grpc/proto-loader');
const path = require('path');

const PROTO_PATH = path.join(__dirname, 'proto', 'route_search.proto');
const packageDefinition = protoLoader.loadSync(PROTO_PATH, {
    keepCase: true, longs: String, enums: String, defaults: true, oneofs: true
});
const routeSearchProto = grpc.loadPackageDefinition(packageDefinition);

console.log("Connecting to C++ Server on localhost:50051...");
const client = new routeSearchProto.RouteSearchService(
    'localhost:50051',
    grpc.credentials.createInsecure()
);

console.log("🚀 Sending PathRequest: London -> Berlin");
client.FindCheapestPath({ source_id: "Paris", destination_id: "Berlin" }, (err, response) => {
    if (err) {
        console.error("❌ Error from C++ Server:", err.message);
    } else {
        console.log("✅ Success! Response from C++:");
        console.log(JSON.stringify(response, null, 2));
    }
});
