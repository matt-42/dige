
all: xslthl-2.0.2.jar
	java -cp /usr/share/java/xalan.jar:./xslthl-2.0.2.jar  	\
	org.apache.xalan.xslt.Process  -in dige.xml -xsl docbook.xsl \
	| sed 's/Loading Xslthl configuration from file.*$///' \
	| sed  's/<\/head>/\n<google analytics>\n&\n/' \
	| sed  -e '/<google analytics>/  {r ga.txt' -e';d}' > index.html

xslthl-2.0.2.jar:
	mkdir -p /tmp/xslthl
	cd /tmp/xslthl ; \
	wget http://sourceforge.net/projects/xslthl/files/xslthl/2.0.2/xslthl-2.0.2.zip ; \
	unzip xslthl-2.0.2.zip
	mv /tmp/xslthl/xslthl-2.0.2.jar .
