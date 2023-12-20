import express from "express";
import path from "path";
import url from "url";

const app = express();

app.use(express.static(path.join(path.dirname(url.fileURLToPath(import.meta.url)))));

app.get("/", (req, res) => {
    return res
        .header("Access-Control-Allow-Origin", "*")
        .status(200)
        .sendFile(path.join(path.dirname(url.fileURLToPath(import.meta.url)), "index.html"));
});

app.listen(3000, console.info);
