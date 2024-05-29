POST http://{{host}}/api/v1/attempt
file,post_attempt_pass.json;
HTTP 200
[Asserts]
jsonpath "$.status" == "PASS"
