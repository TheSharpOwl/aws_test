#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <iostream>

int main() {
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.endpointOverride = Aws::String("S3-API endpoint");
    clientConfig.scheme = Aws::Http::Scheme::HTTP;
    Aws::S3::S3Client client(Aws::Auth::AWSCredentials("minioadmin", "miniokey"), clientConfig,
                             Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);

    Aws::S3::Model::PutObjectRequest putObjectRequest;
    putObjectRequest.SetContentType("image/jpeg");
    Aws::String bucketName = "myBucketName";
    Aws::String fileName = "myFile.jpg";
    putObjectRequest.SetBucket(bucketName.c_str());
    putObjectRequest.WithKey(fileName.c_str());

    auto inputData = Aws::MakeShared<Aws::StringStream>(
            "PutObjectInputStream",
            fileName.c_str(),
            std::stringstream::in | std::stringstream::binary);

    putObjectRequest.SetBody(inputData);
    auto result = client.PutObject(putObjectRequest);
    if (result.IsSuccess()) {
        std::cout << "PutObject completed" << std::endl;
    } else {
        std::cout << "PutObject error: " << result.GetError().GetExceptionName() << " " << result.GetError().GetMessage() << std::endl;
    }

    Aws::ShutdownAPI(options);

    return 0;
}
