var body = $request.body;
var jsonObject = JSON.parse(body);
var url = $request.url;

if(url.indexOf('batch') != -1{
    jsonObject.requests.forEach(function(request) {
        var bodyObject = JSON.parse(request.body);
        if (bodyObject.id === "health_refill_reactive") {
            bodyObject.isFree = true;
        }
        request.body = JSON.stringify(bodyObject);
    });
}

$done({body});
