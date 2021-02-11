FROM alpine:edge 

RUN apk update \
&& apk add -u --no-cache \ 
alpine-sdk \
qt5-qtbase-dev \
qt5-qtquick3d-dev \
qt5-qtquickcontrols \
qt5-qtquickcontrols2-dev \
qt5-qtserialport-dev \
qt5-qtserialbus-dev \
qt5-qtcharts-dev \
qt5-qtlocation-dev \
cppcheck \
clazy \
py-pip \
&& pip install compiledb
