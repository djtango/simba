[@bs.val] external slackToken : string = "process.env.SLACK_TOKEN";

let fetchSimsHistory = (next) => {
  let headers = Https.httpHeaders(~contentType="application/x-www-form-urlencoded");
  let slackAPI = "/api/channels.history" ++ "?token=" ++ slackToken ++ "&channel=CCXETB0DQ";
  let urlOpts = Https.urlOpts(~host="slack.com", ~path=slackAPI, ~headers=headers);
  Https.get(urlOpts, (r) => {
    next(r);
  });
};


