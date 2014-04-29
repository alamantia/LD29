// working with the canvas for a possible project
// test basic tweening .. other random things
var ctx;
var canvas;
function deg2rad ( d ) {
    return d * Math.PI / 180 
}

function rad2deg ( r ) {
    return r / Math.PI * 180 
}

// rotate a point around some origin 
//  needs radius specification
function rotate(x, y, center_x, center_y, a) {
    var translate_x = x - center_x;
    var translate_y = y - center_y;
    var cosa = Math.cos(deg2rad(a));
    var sina = Math.sin(deg2rad(a)); 
    var t_x = translate_x  * cosa  + translate_y * sina + center_x;
    var t_y = -translate_x * sina + translate_y * cosa + center_y;
    var result = {};
    result["x"] = t_x;
    result["y"] = t_y;
    return result;
}

var rot = 0.0;
function draw_segment(x, y, size) {
    ctx.beginPath();
    ctx.fillStyle 	= "#666666";
    ctx.lineWidth 	= 1.0;
    ctx.strokestyle = "#666666";
 
    for (var i = 0; i < 360; i += 360/6) {
        var x1 = Math.cos(deg2rad(i)) * size;
        var y1 = Math.sin(deg2rad(i)) * size;
        var x2 = Math.cos(deg2rad(i)) * (size + 10);
        var y2 = Math.sin(deg2rad(i)) * (size + 20);
    }
    
    for (var i = 0; i <= 360; i += 360/6)  {
        var x1 = Math.cos(deg2rad(i)) * size;
        var y1 = Math.sin(deg2rad(i)) * size;
        if (i == 0) {
            var r = rotate(x1+x, y1+y, x, y, rot);
            ctx.moveTo(r["x"], r["y"]);
        }
        var r = rotate(x1+x, y1+y, x, y, rot);
        ctx.lineTo(r["x"], r["y"]);
    }

    ctx.stroke();
    ctx.closePath();

    ctx.beginPath();
    ctx.fillStyle = "#666666";
    ctx.lineWidth = 1.0;
    ctx.strokestyle = "#666666";
    
    for (var i = 0; i <= 360; i += 360/6)  {
        var x1 = Math.cos(deg2rad(i)) * (size + 20);
        var y1 = Math.sin(deg2rad(i)) * (size + 20);
        
        if (i == 0) {
            var r = rotate(x1+x, y1+y, x, y, rot);
            ctx.moveTo(r["x"], r["y"]);
        }
        var r = rotate(x1+x, y1+y, x, y, rot);
        ctx.lineTo(r["x"], r["y"]);
    }
    
    ctx.stroke();
    ctx.closePath();
}

function mousedown(event) {
    rot += 30.0;
    
    var x = event.clientX;
    var y = event.clientY;
    
    var canvas = document.getElementById("canvas");
    x -= canvas.offsetLeft;
    y -= canvas.offsetTop;
    
    console.log(x + " " + y);
}

function keydown(event) {
    console.log("keydown");
    rot += 30.0;
}

function init() {
    canvas = document.getElementById("canvas");
    ctx = $('#canvas')[0].getContext("2d");
    setInterval(draw, 25);
    window.onkeydown = function (event) {
        keydown(event);
    }
    canvas.onmousedown = function (event) {
        mousedown(event);
    }
}

function draw() {
    ctx.globalCompositeOperation = 'destination-over';
    ctx.fillStyle = "#111111";
    ctx.clearRect(0,0, canvas.width, canvas.height);
    ctx.fillStyle = "#10A301";
    draw_segment(canvas.width/2,canvas.height/2, 50);
    draw_segment(canvas.width/2,canvas.height/2, 70);
    draw_segment(canvas.width/2,canvas.height/2, 90);
    draw_segment(100,100, 10);
    draw_segment(400,100, 20);
}




