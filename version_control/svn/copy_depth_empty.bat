svnadmin create --fs-type fsfs copy_depth_empty.repo

set PWD_WITH_FORWARD_SLASHES=%CD:\=/%

@rem add a file {
svn co file:///%PWD_WITH_FORWARD_SLASHES%/copy_depth_empty.repo copy_depth_empty.co

svn mkdir    copy_depth_empty.co\foo
echo  text > copy_depth_empty.co\foo\file_1.txt

svn add      copy_depth_empty.co\foo
svn ci       copy_depth_empty.co\foo            -m "+ file_1.txt"

rmdir /s /q  copy_depth_empty.co
@rem }

@rem check out empty {
svn co file:///%PWD_WITH_FORWARD_SLASHES%/copy_depth_empty.repo copy_depth_empty.co     --depth empty
svn up                                                          copy_depth_empty.co/foo --depth empty                                                     
@rem }

@rem copy {
svn copy copy_depth_empty.co/foo copy_depth_empty.co/bar
svn up                           copy_depth_empty.co/bar   --set-depth infinity
dir                              copy_depth_empty.co\bar
@rem
