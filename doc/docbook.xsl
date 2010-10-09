<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:fo="http://www.w3.org/1999/XSL/Format"
                xmlns:xslthl="http://xslthl.sf.net"
                exclude-result-prefixes="xslthl">

  <xsl:import href="/usr/share/xml/docbook/stylesheet/nwalsh/html/docbook.xsl"/>
  <xsl:import href="/usr/share/xml/docbook/stylesheet/nwalsh/html/highlight.xsl"/>

  <xsl:param name="highlight.source" select="1"/>
  <xsl:param name="highlight.xslthl.config">file:./xslthl-2.0.2/conf.xml</xsl:param>
  <xsl:param name="html.stylesheet">style.css</xsl:param>

  <xsl:template match='xslthl:comment' mode="xslthl">
    <span class="hl-comment" style="color: #800"><xsl:apply-templates mode="xslthl"/></span>
  </xsl:template>

  <xsl:template match='xslthl:keyword' mode="xslthl">
    <span class="hl-keyword" style="color: #008"><xsl:apply-templates mode="xslthl"/></span>
  </xsl:template>

  <xsl:template match='xslthl:number' mode="xslthl">
    <span class="hl-number" style="color: #066"><xsl:apply-templates mode="xslthl"/></span>
  </xsl:template>

  <xsl:template match='xslthl:string' mode="xslthl">
    <span class="hl-string" style="color: #080"><xsl:apply-templates mode="xslthl"/></span>
  </xsl:template>

  <xsl:template match='xslthl:directive' mode="xslthl">
    <span class="hl-directive" style="color: #402080"><xsl:apply-templates mode="xslthl"/></span>
  </xsl:template>

  <xsl:template match="code">
    <xsl:call-template name="inline.monoseq">
      <xsl:with-param name="content">
        <xsl:call-template name="apply-highlighting"/>
      </xsl:with-param>
    </xsl:call-template>
  </xsl:template>

</xsl:stylesheet>
