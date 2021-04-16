const express = require('express')
const bodyParser = require('body-parser')
const multer = require('multer');

let playlist;

const app = express();
app.use(bodyParser.urlencoded({ extended: true }));

app.get('/', function (req, res) {
    // res.sendFile(__dirname + '/main.html');
    res.sendFile(__dirname + '/submitsuccess.html');
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
    // console.log(files)
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

app.post('/play', (req, res) => {
    
});

app.listen(3000, () => console.log('Server started on port 3000'));
