#!/bin/bash
echo "Boot"
nginx -c /app/nginx.conf

# spawn the fcgi app on port 8000 with no fork
spawn-fcgi -p 8000 -n fastcgir
