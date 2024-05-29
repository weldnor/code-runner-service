POST http://{{host}}/api/v1/attempt
file,post_attempt_fail.json;
HTTP 200
[Asserts]
jsonpath "$.status" == "FAIL"
