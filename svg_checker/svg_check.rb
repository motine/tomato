#!/usr/bin/env ruby
# Draws the SVG (simplified)
# if there are multiple paths overlapping, the lines in the resulting image will appear darker than the rest.
# See the reference cross in the top left to compare the color.

require 'rubygems'
require 'chunky_png'
require "rexml/document"

raise "Please call the script with a SVG as first parameter" if ARGV.size == 0
source_file_path = File.absolute_path(ARGV[0])
target_file_path = File.join(File.dirname(source_file_path), "#{File.basename(source_file_path, ".*")}.png")

png = ChunkyPNG::Image.new(1500, 1500, ChunkyPNG::Color::TRANSPARENT)
color = ChunkyPNG::Color.rgba(100, 100, 100, 50)

# Draw the reference
png.line(30, 15, 30, 45, color)
png.line(15, 30, 45, 30, color)

doc = REXML::Document.new(File.read(source_file_path))

REXML::XPath.each(doc, "//path") do |path|
  # color = ChunkyPNG::Color.rgba(rand(200), rand(200), rand(200), 150)
  d_attr = path.attributes["d"]
  first_dot_x, first_dot_y = nil, nil
  last_dot_x, last_dot_y = nil, nil

  d_attr.scan(/[lcamLCAM] \d+.\d+ \d+.\d+ ?[Zz]?/) do |dot_match|
    type, x, y, closed = dot_match.to_s.match(/([lcamLCAM]) (\d+.\d+) (\d+.\d+)( [zZ])?/).captures
    x,y = x.to_i, y.to_i
    draw_line = ["L", "C", "A"].include?(type.upcase) # "M" is for move to
    puts "found curveto in path, using a straight line instead" if type.upcase == "C"
    puts "found arcto in path, using a straight line instead" if type.upcase == "A"
    if draw_line && !last_dot_x.nil? then
      png.line(last_dot_x, last_dot_y, x, y, color)
    end

    if !closed.nil? then
      png.line(first_dot_x, first_dot_y, x, y, color)
    end

    first_dot_x, first_dot_y = x,y if type.upcase == "M"
    last_dot_x, last_dot_y = x,y
  end
end

png.save(target_file_path, :interlace => true)
