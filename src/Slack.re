[@bs.val] external slackToken : string = "process.env.SLACK_TOKEN";
[@bs.val] external slackChannel : string = "process.env.SLACK_CHANNEL";

[@bs.deriving abstract]
type slackMessage = {
  text: string,
  ts: string
};

[@bs.deriving abstract]
type slackHistoryPayload = {
  ok: bool,
  messages: array(slackMessage)
};

let parseResponse: (Https.response) => slackHistoryPayload = [%bs.raw {|
  function (res) {
    return JSON.parse(res);
  }
|}];

let fetchSimsHistory = (next) => {
  let headers = Https.httpHeaders(~contentType="application/x-www-form-urlencoded");
  let slackAPI = "/api/channels.history" ++ "?token=" ++ slackToken ++ "&channel=" ++ slackChannel;
  let urlOpts = Https.urlOpts(~host="slack.com", ~path=slackAPI, ~headers=headers);
  Https.get(urlOpts, (r) => {
    next(parseResponse(r));
  });
};

let extractMessageTextFromPayload = (payload) => {
  Js.log(Array.map((m) => textGet(m), messagesGet(payload)));
  ()
};

fetchSimsHistory((r) => {
  extractMessageTextFromPayload(r);
})
