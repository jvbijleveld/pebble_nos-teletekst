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
  var raw;
  var regex = /(<([^>]+)>)/ig;
  
  console.log('Andd now: the news...' + contentArr.length);
  for (var i = 1; i < contentArr.length; i++) { //first index contains markup
    raw = contentArr[i].replace(regex, "");
   
    raw = cleanUpSpecialChars(raw);
    console.log("raw:" + raw);
    textData = textData + raw.substr(0,35) + " ";
    if(i<9){
      linkData = linkData + findLinkInLine(contentArr[i]);
    }
  }
  sendToPebble(textData,linkData);
}

function sendToPebble(ttData, linksData){
  //console.log(ttData);
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
  //console.log('strpos: ' + strpos + ' in line: '+ line);
  if(strpos >= 0){
    return line.substr(strpos+7,3) + ",";
  }else{
    return "";
  }
}

function getPage(pageNr) {
  console.log("Getting page" + pageNr);
  var url = 'http://teletekst-data.nos.nl/json/' + pageNr;
  xhrRequest(url, 'GET', function(responseText) {
    //console.log(responseText);
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
   var dict = e.payload;
    console.log('Got message: ' + JSON.stringify(dict));
    console.log("Going for page: " + dict[2]);
    getPage(dict[2]);
  }                     
);

function cleanUpSpecialChars(str){
  str = str.replace(/[ÀÁÂÃÄÅ]/g,"A");
  str = str.replace(/[àáâãäå]/g,"a");
  str = str.replace(/[ÈÉÊË]/g,"E");
  str = str.replace(/[èéêë]/g,"e");
  str = str.replace(/[ÌÍÎÏ]/g,"I");
  str = str.replace(/[ìíîï]/g,"i");
  str = str.replace(/[ÒÓÔÖ]/g,"O");
  str = str.replace(/[òóôö]/g,"o");
  str = str.replace(/[ÙÚÛÜ]/g,"U");
  str = str.replace(/[ùúûü]/g,"u");
  return str; // final clean up
}

function HtmlDecode(s) {
 return s.replace(/&[a-z]+;/gi, function(entity) {
  switch (entity) {
  case '&Agrave;': return "A";
  case '&Aacute;': return "A";
  case '&Acirc;': return "A";
  case '&Atilde;': return "A";
  case '&Auml;': return "A";
  case '&Aring;': return "A"; 
  case '&agrave;': return "a";
  case '&aacute;': return "a";
  case '&acirc;': return "a";
  case '&atilde;': return "a";
  case '&auml;': return "a";
  case '&aring;': return "a";       
  case '&Egrave;': return "E";
  case '&Eacute;': return "E";
  case '&Ecirc;': return "E";
  case '&Etilde;': return "E";
  case '&Euml;': return "E";
  case '&Ering;': return "E";       
  case '&egrave;': return "e";
  case '&eacute;': return "e";
  case '&ecirc;': return "e";
  case '&etilde;': return "e";
  case '&euml;': return "e";
  case '&ering;': return "e";
  case '&Ograve;': return "O";
  case '&Oacute;': return "O";
  case '&Ocirc;': return "O";
  case '&Otilde;': return "O";
  case '&Ouml;': return "O";
  case '&Oring;': return "O"; 
  case '&ograve;': return "o";
  case '&oacute;': return "o";
  case '&ocirc;': return "o";
  case '&otilde;': return "o";
  case '&ouml;': return "o";
  case '&oring;': return "o";
  case 'ö': return "o";
  case '&Ugrave;': return "U";
  case '&Uacute;': return "U";
  case '&Ucirc;': return "U";
  case '&Utilde;': return "U";
  case '&Uuml;': return "U";
  case '&Uring;': return "U"; 
  case '&ugrave;': return "u";
  case '&uacute;': return "u";
  case '&ucirc;': return "u";
  case '&utilde;': return "u";
  case '&uuml;': return "u";
  case '&uring;': return "u";            
  
  case '&Igrave;': return "I";
  case '&Iacute;': return "I";
  case '&Icirc;': return "I";
  case '&Itilde;': return "I";
  case '&Iuml;': return "I";
  case '&Iring;': return "I"; 
  case '&igrave;': return "i";
  case '&iacute;': return "i";
  case '&icirc;': return "i";
  case '&itilde;': return "i";
  case '&iuml;': return "i";
  case '&iring;': return "i";      
      
  default: return '';
  }
 });
}