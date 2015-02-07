# SVG Checker

This is a very simple check script, to identify duplicate paths. Just run `bundle install` on your machine and the you can execute `ruby svg_check.rb [PATH_TO_SVG]`. The script will the create a PNG in the same directory with the same name like the SVG.

After running the script, you can compare the color of the reference cross on the top left with the other lines in the PNG. If the SVG's paths seem darker, then you have duplicate paths.

WARNING: the SVG is very much simplified and does not support anything else then straight paths (arcs and curves are approximated by lines). Any other shapes then paths are silently ignored!

I tested this script on Ruby 2.2.0, but I don't see why it should not work with earlier versions.