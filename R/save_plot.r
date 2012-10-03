#
# r --vanilla -f save_plot.r
#
# http://stackoverflow.com/questions/7144118/how-to-save-a-plot-as-image-on-the-disk
#

x <- seq (-5, 5, 0.1)
y <- sin(x)

png(filename = "saved.png")
plot(x,y, type="l")
dev.off()
