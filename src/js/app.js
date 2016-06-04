var contentSplit = '<span class="cyan "> ';

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function parsePageData(data){
  var contentArr = data.content.split(contentSplit);
  
  console.log('Andd now: the news...' + contentArr.length);
  for (var i = 1; i < contentArr.length; i++) { //first index contains markup
    console.log(contentArr[i].substr(0,35));
  }
}


function getPage(pageNr) {
  var url = 'http://teletekst-data.nos.nl/json/' + pageNr;
  xhrRequest(url, 'GET', function(responseText) {
    console.log(responseText);
    parsePageData(JSON.parse(responseText));
  });
}

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log("PebbleKit JS ready!");
    getPage(101);
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log("AppMessage received!");
    getPage(101);
  }                     
);
