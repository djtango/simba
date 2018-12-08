echo "Testing /slack/events... by sending canned slack event"
# real_json=`cat ./change_status.json`
real_json=`cat ./url_verification_event.json`


curl -X POST -d "$real_json" -H "Content-Type: application/json" localhost:9000/slack/events
