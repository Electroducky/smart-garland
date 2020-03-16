#ifndef GARLAND_WEB_PAGES
#define GARLAND_WEB_PAGES

#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/anim" id="usrform">
    <input type="submit" value="Submit">
  </form>
  </br>
  <textarea rows="20" cols="80" name="anim" form="usrform"></textarea>
</body></html>
)rawliteral";

#endif //GARLAND_WEB_PAGES