import skia

surface = skia.Surface(24, 24)

with surface as canvas:
    paint = skia.Paint(AntiAlias=True, Color=skia.ColorRED)
    canvas.drawString('1', 0, 0, skia.Font(None, 24), paint)

image = surface.makeImageSnapshot()
image.save('output.png', skia.kPNG)