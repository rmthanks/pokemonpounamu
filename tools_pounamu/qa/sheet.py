import sys,os
from PIL import Image
d=sys.argv[1]; fs=sorted(f for f in os.listdir(d) if f.endswith('.png') and not f.startswith('sheet'))
if len(sys.argv)>2: fs=[f for f in fs if f.split('_')[0] in sys.argv[2].split(',')]
ims=[Image.open(os.path.join(d,f)).resize((240,160)) for f in fs]
cols=5; rows=(len(ims)+cols-1)//cols
sh=Image.new('RGB',(240*cols,160*rows),'white')
for i,im in enumerate(ims): sh.paste(im,((i%cols)*240,(i//cols)*160))
sh.save(os.path.join(d,'sheet.png')); print(len(ims),'frames')
