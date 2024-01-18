import express from "express";
import path from "path";
import url from "url";

const __dirname = path.dirname(url.fileURLToPath(import.meta.url));
const __assets_dir = path.join(__dirname, "..", "assets");

const app = express();

app.use(express.static(__dirname));
app.use(express.static(__assets_dir));

app.get("/", (req, res) => {
    return res
        .header("Access-Control-Allow-Origin", "*")
        .status(200)
        .sendFile(path.join(__dirname, "index.html"));
});

app.listen(3000, console.info);
