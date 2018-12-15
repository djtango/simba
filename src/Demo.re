/* Js.log("Hello, BuckleScript and Reason!"); */
type express;
type response;
type handler = (string, response) => unit;
[@bs.send] external get : (express, string, handler) => unit = "";
[@bs.send] external send : (response, string) => unit = "";
[@bs.send] external listen : (express, int) => unit = "";
[@bs.module] external express : unit => express = "express";

let app = express();
get(app, "/", (_, res) => {
  send(res, "hi");
});

listen(app, 9000)
