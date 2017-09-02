# https://cdnjs.cloudflare.com/ajax/libs/vue/2.4.2/vue.js
# https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.0.0-beta/js/bootstrap.min.js
# https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js

echo "Descargando dependencias web page"
echo "Descargando vuejs"
wget https://cdnjs.cloudflare.com/ajax/libs/vue/2.4.2/vue.js -q -P web_server/ > /dev/null
# echo "Descargando bootstrap"
# wget https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js -q -P web_server/
# wget https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css -q -P web_server/
echo "Descargando jquery"
wget https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js -q -P web_server/
echo "Descargando materialize"
wget https://cdnjs.cloudflare.com/ajax/libs/materialize/0.100.1/js/materialize.min.js -q -P web_server/
wget https://cdnjs.cloudflare.com/ajax/libs/materialize/0.100.1/css/materialize.min.css -q -P web_server/
wget https://cdnjs.cloudflare.com/ajax/libs/materialize/0.100.1/fonts/roboto/Roboto-Regular.woff2 -q -P web_server/fonts/roboto
wget https://cdnjs.cloudflare.com/ajax/libs/materialize/0.100.1/fonts/roboto/Roboto-Regular.woff -q -P web_server/fonts/roboto
