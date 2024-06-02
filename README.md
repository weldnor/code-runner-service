# Code Runner Service

## Demo

[video here](https://drive.google.com/file/d/1lI4yzwkMXx2tgHSxYtfmNu6B9I9HHofM/view?usp=sharing)

## Requirements

[here](https://docs.google.com/document/d/1lSAybgVEM3qTog4T71DDacfdeO7ui5ABqPoZEYObTP8/edit?usp=sharing)

## Build & run

via cmake:

```shell
cmake -S . -B ./build -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=FALSE && \
cmake --build ./build --config Release -j8
./app/CRS
```

via Docker:

```shell
docker build . --tag crs
docker run -p 8000:8000 crs
```

## Test

Api tests:

```shell
cd ./api-tests
./test.sh
```

## API Reference

### Get service status

#### Request

GET /api/v1/health

#### Response

```json
{
  "status": "PASS"
}
```

### Post attempt

#### Request

POST /api/v1/attempt

Params:

- code (string)
- lang (string, cpp or python)
- tests (array of {input: <string>, expected: <string>})

Python example:

```json
{
  "code": "f = open(\"input.txt\")\nline = f.readline()\nf.close()\n\na = int(line.split(\" \")[0])\nb = int(line.split(\" \")[1])\n\nf = open(\"output.txt\", \"w\")\nf.write(str(a + b))\nf.close()",
  "lang": "python",
  "tests": [
    {
      "input": "2 2",
      "expected": "4"
    },
    {
      "input": "4 4",
      "expected": "8"
    },
    {
      "input": "1000000000 1000000000",
      "expected": "2000000000"
    }
  ],
  "timeout_s": 1
}
```

Cpp example:

```json
{
  "code": "#include <iostream>\n#include <fstream>\n\nint main() {\n    std::ifstream inputFile(\"input.txt\");\n    std::ofstream outputFile(\"output.txt\");\n\n    if (!inputFile ||!outputFile) {\n        std::cerr << \"Error: Unable to open input or output file.\" << std::endl;\n        return 1;\n    }\n\n    int num1, num2, sum;\n    inputFile >> num1 >> num2;\n\n    if (inputFile.fail()) {\n        std::cerr << \"Error: Invalid input in input.txt.\" << std::endl;\n        return 1;\n    }\n\n    sum = num1 + num2;\n    outputFile << sum;\n\n    inputFile.close();\n    outputFile.close();\n\n    return 0;\n}",
  "lang": "cpp",
  "tests": [
    {
      "input": "2 2",
      "expected": "4"
    },
    {
      "input": "100 100",
      "expected": "200"
    }
  ],
  "timeout_s": 1
}
```

#### Response

If the tests run successfully...

```json
{
  "status": "OK"
}
```

...or else

```json
{
  "status": "FAIL"
}
```
