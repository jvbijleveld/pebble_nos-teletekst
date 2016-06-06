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
  var textData = '';
  var linkData = '';
  
  console.log('Andd now: the news...' + contentArr.length);
  for (var i = 1; i < contentArr.length; i++) { //first index contains markup
    textData = textData + contentArr[i].substr(0,35) + "|";
    linkData = linkData + findLinkInLine(contentArr[i]) + "|";
    console.log(textData);
  }
  sendToPebble(textData,linkData);
}

function sendToPebble(ttData, linksData){
  console.log(ttData);
  var dictionary = {
    "KEY_TT_DATA": ttData,
    "KEY_TT_LINKS": linksData
  };
      
  Pebble.sendAppMessage(dictionary,
    function(e) {
      console.log('TT Data sent to Pebble successfully!');
    },
    function(e) {
      console.log('Error sending TT data to Pebble!');
    }
  );
}

function findLinkInLine(line){
  var strpos = line.indexOf('href=');
  if(strpos){
    return line.substr(strpos+7,3);
  }else{
    return false;
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
