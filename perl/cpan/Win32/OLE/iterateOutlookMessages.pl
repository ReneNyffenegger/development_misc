use warnings;
use strict;

# helpful links
# 
#    http://stackoverflow.com/questions/11654941/perl-win32ole-and-microsoft-outlook-iterating-through-email-attachments-eff
#


use Win32::OLE;   # qw (in with)
use Win32::OLE::Const 'Microsoft Outlook';
use Win32::OLE::Variant;

my $OL = Win32::OLE->GetActiveObject('Outlook.Application') || Win32::OLE->new('Outlook.Application', 'Quit');

die unless $OL;

my $NameSpace = $OL->GetNameSpace("MAPI") or die;

my $Folder = $NameSpace->GetDefaultFolder(olFolderInbox);

foreach my $msg (Win32::OLE::in($Folder->{Items})) {

 # print join "\n", keys %{$msg};

  print "\n", $msg->{Subject}, "\n";
  print "  ", $msg->{CreationTime}, "\n";


  my $sender = $msg->{Sender};
  print "  ", $sender-> {Name}, "  ", $sender->{Address}, "\n"; # $sender->{ID}, "\n";
  print "  ", $msg->{SenderName}, "\n"; # Equal to $msg->{Sender}->{Name} ?
  print "  ", $msg->{CC}, "  ", $msg->{BCC}, "\n";


# print "  ", $msg ->{BodyFormat}, "\n";

  for my $attachment (Win32::OLE::in($msg->{Attachments})) {

#   print join "\n... ", keys(%$attachment);
    print "    ", $attachment->{FileName}, # "  PathName:", $attachment->{PathName}, 
          "  "  , $attachment->{Size}, "\n";

#   $attachment -> SaveAsFile(...);

  }

}

