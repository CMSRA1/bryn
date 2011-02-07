
import errno

import ROOT as Root
import math
from time import strftime
import os, commands

def ensure_dir(path):
    try:
      os.makedirs(path)
    except OSError as exc: # Python >2.5
      if exc.errno == errno.EEXIST:
        pass
      else: raise





def HistogramMaxY(H):
   Nbins = H.GetNbinsX()
   Entries = [H.GetBinContent(i) for i in range(1,Nbins+1)]
   return max(Entries)

def HistogramMinX(H):
  Nbins = H.GetNbinsX()
  for x in range(0,Nbins):
    if H.GetBinContent(x) != 0:
      return H.GetBinLowEdge(x+1)
  return 0

def HistogramMaxX(H):
  Nbins = H.GetNbinsX()
  BackItr = range(0,Nbins)
  BackItr.reverse()
  for x in BackItr :
    if H.GetBinContent(x) != 0:
      return H.GetBinLowEdge(x+1)



def Systematics(H1,H2,H3,Smeared,outType):
  if outType == "TGraph":   Standard = Root.TGraphAsymmErrors(H1)
  if outType == "TH1":  Standard = H1.Clone()
  UpperError = H2.Clone()
  LowerError = H3.Clone()
  SmearDown = 0.
  SmearUp = 0.
  up = 0.
  down = 0.
  for bin in range(1,H1.GetNbinsX()+1):
    if H1.GetBinContent(bin)-Smeared.GetBinContent(bin) < 0.:
      SmearDown = 0.
      SmearUp = (H1.GetBinContent(bin)-Smeared.GetBinContent(bin))**2
      # print H1.GetBinCenter(bin),H1.GetBinContent(bin), SmearUp
    if H1.GetBinContent(bin)-Smeared.GetBinContent(bin) > 0.:
      SmearDown =(H1.GetBinContent(bin)-Smeared.GetBinContent(bin))**2# 0.
      SmearUp = 0.
    if H1.GetBinContent(bin) - LowerError.GetBinContent(bin) > 0.:
      down = (H1.GetBinContent(bin) - LowerError.GetBinContent(bin))**2
    if H1.GetBinContent(bin) - LowerError.GetBinContent(bin) < 0.:
      up = (H1.GetBinContent(bin) - LowerError.GetBinContent(bin))**2
    if UpperError.GetBinContent(bin)-H1.GetBinContent(bin) > 0.:
      up = (UpperError.GetBinContent(bin)-H1.GetBinContent(bin))**2
    if UpperError.GetBinContent(bin)-H1.GetBinContent(bin) < 0.:
      down = (UpperError.GetBinContent(bin)-H1.GetBinContent(bin))**2
      # print H1.GetBinCenter(bin),H1.GetBinContent(bin), SmearDown
    if outType == "TGraph":
      Standard.SetPointError(bin-1, H1.GetBinWidth(bin)/2, H1.GetBinWidth(bin)/2,math.sqrt((H1.GetBinError(bin))**2 + down + SmearDown), math.sqrt((H1.GetBinError(bin))**2 + up + SmearUp))
      # Standard.SetPointEYlow(bin,math.sqrt((H1.GetBinError(bin))**2 + (H1.GetBinContent(bin)-LowerError.GetBinContent(bin))**2))
      # print "bin",H1.GetBinCenter(bin), H1.GetBinContent(bin)," Satat error " , H1.GetBinError(bin), "sys Error", (H1.GetBinContent(bin)-LowerError.GetBinContent(bin)), "total", math.sqrt((H1.GetBinError(bin))**2 + (H1.GetBinContent(bin)-LowerError.GetBinContent(bin))**2),"erros in tgraph errors:",  Standard.GetErrorYlow(bin), Standard.GetErrorYhigh(bin)
    # if outType == "TGraph": Standard.SetPointEYhigh(bin,math.sqrt((H1.GetBinError(bin))**2 + (UpperError.GetBinContent(bin)-H1.GetBinContent(bin))**2))
    if outType == "TH1": Standard.SetBinError(bin, math.sqrt((Standard.GetBinError(bin))**2 + ((UpperError.GetBinContent(bin) - LowerError.GetBinContent(bin))/2)**2+SmearUp) )
  return Standard
  # return True

def SystematicsSmear(H1,H2):
  """docstring for Systematics"""
  Standard = H1.Clone()
  Smeared = H2.Clone()
  for bin in range(1,Standard.GetNbinsX()+1):
    StandardUpper = math.sqrt((Standard.GetBinError(bin))**2 + (Standard.GetBinContent(bin)-Smeared.GetBinContent(bin))**2)
    # print  "Bin",Standard.GetBinCenter(bin),Standard.GetBinContent(bin),"bin error" ,Standard.GetBinError(bin)
    Standard.SetBinError(bin, StandardUpper)
  return Standard
  pass




def Header(intLumi):
  """docstring for Header"""
  header = '''
  <html>
  <head>
    <title> ''' "RA1 Plots using " +str(intLumi) + "pb of data" + '''


  <style type =\"text/css">
  body {
      margin:0;
      padding:0;
      border:0;
      outline:0;
      font-size:100%;
      vertical-align:baseline;
      background:#FFFFCC;
  }

  body {
      line-height:1;
  }

  article,aside,details,figcaption,figure,
  footer,header,hgroup,menu,nav,section {
    display:block;
  }

  nav ul {
      list-style:none;
  }

  blockquote, q {
      quotes:none;
  }

  blockquote:before, blockquote:after,
  q:before, q:after {
      content:'';
      content:none;
  }

  a {
      margin:0;
      padding:0;
      font-size:100%;
      vertical-align:baseline;
      background:transparent;
  }

  /* change colours to suit your needs */
  ins {
      background-color:#ff9;
      color:#000;
      text-decoration:none;
  }

  /* change colours to suit your needs */
  mark {
      background-color:#ff9;
      color:#000;
      font-style:italic;
      font-weight:bold;
  }

  del {
      text-decoration: line-through;
  }

  abbr[title], dfn[title] {
      border-bottom:1px dotted;
      cursor:help;
  }

   table {
   display: table;
   border-collapse: separate;
   border-spacing: 2px;
   border-color: gray; }

  /* change border colour to suit your needs */
  hr {
      display:block;
      height:1px;
      border:0;
      border-top:1px solid #cccccc;
      margin:1em 0;
      padding:0;
  }

  input, select {
      vertical-align:middle;
  }
  </style>

  <script type="text/JavaScript">
  <!-- Chief...
  function toggle(d)
  {
    var o=document.getElementById(d);
    o.style.display=(o.style.display=='none')?'block':'none';
  }
  -->
  </script>

    </head>
  <!-- Page navigation menu -->
  <body>
  <CENTER>
  <h1>Comparison of Basic quantities for N=2, N>=3 & N>=2 Jets</h1>
  <P>Data = JetMetTau ''' + str(intLumi) + ''', contact email bryn.mathias AT cern DOT ch</P>'''
  return header

  pass



def BegSec(SectionTitle):
  """docstring for table"""
  start = '''

  <h1> '''+SectionTitle+''' <a href="javascript:;" onClick="toggle(\''''+SectionTitle+ '''\');">Collapse/Expand</a>
  <div id="'''+SectionTitle+'''">\n
<table border="1" bordercolor="#000000" style="background-color:#FFFFCC" width="1200" cellpadding="3" cellspacing="3"> \n
  <p> \n

  </a>
    <tr>
    <td>DiJet</td>
    <td> >=3 Jet</td>
    <td> >=2 Jet </td>
    </tr>'''
  return start
  pass

def EndSec():
  """docstring for EndTable"""
  end = ''' </p>

  </table>
</div>'''
  return end
  pass

def Footer():
  """docstring for Footer"""
  footer = '''
    </CENTER>
    </body>
    </html>'''
  return footer
  pass

def newPlot(hist):
  """docstring for newColumn"""
  Column = "<td>" + hist + "</td>"
  return Column
  pass

def HyperLink(hist):
  """docstring for HyperLink"""
  link = "<td><a href=" + hist + '.png><img src=\"'+  hist + '.png\" width=\"400\" height=\"400\" /></a>'+ "</td> \n"
  return link
  pass





def PlotRow(a,b,c):
  """docstring for PlotRow"""

  row ="<tr>"  + newPlot(a) + newPlot(b) + newPlot(c) + "</tr>" + '\n' + "<tr>" + HyperLink(a) + HyperLink(b) + HyperLink(c) + "</tr> </div> \n"
  return row
  pass

