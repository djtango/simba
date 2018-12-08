type express;
type bodyParser;
type response;
type request;

[@bs.deriving abstract] type reqWithBody = {body: string};

[@bs.deriving abstract] type postBody = {challenge: string};
[@bs.deriving abstract] type postReqWithBody = {body: postBody};

type handler = (reqWithBody, response) => unit;
type eventPostHandler = (postReqWithBody, response) => unit;
type middleware = (request, response, handler) => unit;
type appCb = (string) => unit;
[@bs.send] external get : (express, string, handler) => unit = "";
[@bs.send] external post : (express, string, eventPostHandler) => unit = "";
[@bs.send] external send : (response, string) => unit = "";
[@bs.send] external use : (express, middleware) => unit = "";
[@bs.send] external json : (bodyParser) => middleware = "";
[@bs.send] external listen : (express, int, appCb) => unit = "";
[@bs.module] external express : unit => express = "express";
[@bs.module] external bodyParser : bodyParser = "body-parser";


let app = express();
get(app, "/", (_, res) => {
  send(res, "hi");
});

use(app, json(bodyParser));

post(app, "/slack/events", (req, res) => {
  let body = bodyGet(req);
  let challenge = challengeGet(body);
  send(res, challenge);
});


listen(app, 9000, (err) => {
  Js.log("Listening on port 9000");
})
