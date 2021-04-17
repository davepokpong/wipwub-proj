const express = require('express')
const bodyParser = require('body-parser')
const multer = require('multer');
const exec = require('child_process').exec;

let playlist;
let index=0;

const app = express();
app.use(bodyParser.urlencoded({ extended: true }));

app.get('/', function (req, res) {
    // res.sendFile(__dirname + '/main.html');
    res.sendFile(__dirname + '/main.html');
});

app.get('/returnbtn', function (req, res) {
    res.sendFile(__dirname + '/main.html');
});

app.get('/chk', function (req, res) {
    res.json({
        message: 'WELCOME',
        status: 'Ready!'
    });
});
// SET STORAGE
var storage = multer.diskStorage({
    destination: function (req, file, cb) {
        cb(null, 'uploads')
    },
    filename: function (req, file, cb) {
        cb(null, file.fieldname + '-' + Date.now())
    }
});

var upload = multer({ storage: storage });

function clearName(namefile) {
    var clearly = namefile.split(".");
    console.log(clearly);
    return clearly[0];
}

app.post('/uploadmultiple', upload.array('myFiles', 12), (req, res, next) => {
    const files = req.files
    // console.log(files.length)
    if (!files) {
        const error = new Error('Please choose files')
        error.httpStatusCode = 400
        return next(error)
    }
    // res.send(files);
    // console.log(files);
    playlist = files;
    // console.log(playlist);
    res.sendFile(__dirname + '/submitsuccess.html');
});

app.get('/filename', function (req, res){
    res.send(playlist);
});

app.get('/play', (req, res) => {
    var textname;
    console.log("Playing!");
    playlist.forEach(namequeue => {
        textname += namequeue.filename+' ';
    });
    textname = textname.slice(9);
    console.log(textname);
    
    // const myShellScript = exec(`echo ${playlist[index].originalname}`);
    const myShellScript = exec(`cd uploads; mpg123 ${textname}`);
    // myShellScript.stdout.on('data', (data)=>{
    //     // console.log(data); 
    // });
    // myShellScript.stderr.on('data', (data)=>{
    //     console.error(data);
    // });
    res.json({
        status: 'Playing !'
    });
});

app.listen(3000, () => console.log('Server started on port 3000'));
