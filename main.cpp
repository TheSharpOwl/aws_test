#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include "aws/s3/model/CreateBucketConfiguration.h"
#include "aws/s3/model/CreateBucketRequest.h"
#include <iostream>

int main() {
    const char* rawJsonExample = "{\n}\n";

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.endpointOverride = Aws::String("127.0.0.1:9000");
    clientConfig.scheme = Aws::Http::Scheme::HTTP;
    clientConfig.verifySSL = false;

    Aws::S3::S3Client client(Aws::Auth::AWSCredentials("minioadmin", "miniokey"), clientConfig,
                             Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);

    auto listBucketsResult = client.ListBuckets();
    if (listBucketsResult.IsSuccess()) {
        std::cout << "FINE\n";
    } else {
        std::cout << "NOT OK\n";
        return -1;
    }

    Aws::String bucketName = "anything";
    Aws::String fileName = "myFile.json";

    Aws::S3::Model::CreateBucketRequest request;
    request.SetBucket(Aws::String(bucketName));
    auto outcome = client.CreateBucket(request);

    if(!outcome.IsSuccess())
    {
        if(outcome.GetError().GetExceptionName() != "BucketAlreadyOwnedByYou")
        {
            std::cout << "FAILED TO CREATE A BUCKET\n";
            std::cout << outcome.GetError().GetExceptionName() << " " << outcome.GetError().GetMessage() << "\n";
            return -1;
        }
    }

    Aws::S3::Model::PutObjectRequest putObjectRequest;
    // no set content type because it's json file
    putObjectRequest.SetBucket(bucketName.c_str());
    putObjectRequest.WithKey(fileName.c_str());

    auto inputData = Aws::MakeShared<Aws::StringStream>(
            "PutObjectInputStream",
            fileName.c_str(),
            std::stringstream::in | std::stringstream::binary | std::stringstream::out);

    inputData->write(rawJsonExample, std::string(rawJsonExample).size());

    putObjectRequest.SetBody(inputData);
    auto result = client.PutObject(putObjectRequest);
    if (result.IsSuccess()) {
        std::cout << "PutObject completed" << std::endl;
    } else {
        std::cout << "PutObject error: " << result.GetError().GetExceptionName() << " " << result.GetError().GetMessage() << std::endl;
    }

    return 0;
}
