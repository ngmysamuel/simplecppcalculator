# Simple CPP Calculator
A simple API you can call to add, subtract, multiply, and divide. Plus, exponents.  

Health Check
```
GET https://docker-repo-i4yya62lxq-as.a.run.app/
```  

Add
```
GET https://docker-repo-i4yya62lxq-as.a.run.app/plus/<arg1>/<arg2>
```

Subtract
```
GET https://docker-repo-i4yya62lxq-as.a.run.app/minus/<arg1>/<arg2>
```

Multiply
```
GET https://docker-repo-i4yya62lxq-as.a.run.app/multiply/<arg1>/<arg2>
```

Divide
```
GET https://docker-repo-i4yya62lxq-as.a.run.app/divide/<arg1>/<arg2>
```

Exponent
```
GET https://docker-repo-i4yya62lxq-as.a.run.app/exponent/<arg1>/<arg2>
```

# Building and Running

## Locally
```
git clone https://github.com/ngmysamuel/simplecppcalculator.git
g++ src/app.cpp -o out -lws2_32
./out.exe
```

## GitHub Actions
* Simply push!
    * Step 1: Checkout.
        * This step checks out the code - similar to what you would do in the local build and run step
    * Step 2: Google Auth
        * This authenticates your entire workflow with Google. We will be using their Artifact Repository to store our built image as well as Google Cloud Run to deploy our image.
        * TODO: make a move to Docker Hub?
    * Step 3: Docker Auth
        * Actually authenticates into the Artifact Repository
    * Step 4: Build and Push Container
        * Runs `docker build` and `docker push`
    * Step 5: Deploy to Cloud Run
        * The deployment phase where the image becomes an instance running on Google's cloud infra.
    * Step 6: Show Output
        * Syntactic sugar to provide easy access to the deployed endpoint  

![Workflow Diagram](photo_3.png)

## Issues faced
* Google's documentation on permissioning for GitHub Actions was hard to understand
    * [Workload Identity Federation](https://cloud.google.com/iam/docs/workload-identity-federation)
    * Creation of service accounts, Workload identity pools, Workload identity pool providers, OIDC, local JWKs, attribute mappings, CEL expressions, etc
* Assorted issues 
    * outdated tutorials
    * wrong issuer URI when setting up Federated Identity
    * wrong URI concatenation (missing image name) in docker build/push
    * understanding what Google's Artifact Repository's location meant
    * after deploying to Cloud Run, there was an extra step needed to disable Authentication
* Had to grant permissions but was looking in the wrong place
![Where I was stuck](photo_1.png)
Actual page to grant the roles was at another page  
![Where it should have been](photo_2.PNG)

## Helpful Links
* [Where to get C++ compiler](https://www.mingw-w64.org/downloads/)
* [How to download w64devkit](https://github.com/skeeto/w64devkit)
* [Containerising a C++ application](https://medium.com/codex/a-practical-guide-to-containerize-your-c-application-with-docker-50abb197f6d4)
* [Understanding roles of CMake, make and GCC](https://stackoverflow.com/q/39761924)
* [cpp-httplib](https://github.com/yhirose/cpp-httplib)
*[Header files](https://learn.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=msvc-170)

### Less Helpful Links
* [Setting up Identity Federation and allowing GitHub Actions](https://cloud.google.com/blog/products/identity-security/secure-your-use-of-third-party-tools-with-identity-federation)
* [Helper with the above](https://mahendranp.medium.com/gcp-workload-identity-federation-with-github-actions-1d320f62417c)
* [Deployment Specific - did not really make use of this](https://cloud.google.com/blog/products/devops-sre/deploy-to-cloud-run-with-github-actions)
* [GitHub's perspective on the first link - correct URI found here](https://docs.github.com/en/actions/deployment/security-hardening-your-deployments/configuring-openid-connect-in-google-cloud-platform)
* [List of GCP Locations](https://cloud.google.com/artifact-registry/docs/repositories/repo-locations)

### Some commands used
```
gcloud iam workload-identity-pools providers create-oidc github-actions-oidc \
--workload-identity-pool="github-actions-pool" \
--issuer-uri="https://token.actions.githubusercontent.com" \
--attribute-mapping="google.subject=assertion.sub,attribute.repository=assertion.repository,attribute.repository_owner=assertion.repository_owner,attribute.branch=assertion.sub.extract('/heads/{branch}/')" \
--location=global \
--attribute-condition="attribute.owner==assertion.repository_owner"

gcloud iam service-accounts create deployer-sa --display-name="Deployer Service Account" --description="Deploys the application for you"

gcloud iam service-accounts add-iam-policy-binding deployer-sa@orbital-lacing-281401.iam.gserviceaccount.com \
  --role="roles/iam.workloadIdentityUser" \
--member="principal://iam.googleapis.com/projects/473066013520/locations/global/workloadIdentityPools/github-actions-pool/subject/repo:ngmysamuel/devops_apr_24:ref:refs/heads/main"
```