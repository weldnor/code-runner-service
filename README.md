# Code Runner Service

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
docker run -d crs
```

## API Reference

### Get service status

#### Request

GET /api/v1/health

#### Response

```json
{
  "status": "OK"
}
```

### Post attempt

#### Request

POST /api/v1/attempt

Params:

- code (string)
- lang (string, only python supported now)
- tests (array of {input: })

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
