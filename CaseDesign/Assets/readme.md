# Case Design and Model

## Box4u Case Details

### Base

The base of the case has the following specifications:
- Rounded corners (R6)
- Outer dimensions approximately 122/121.3 mm (width) and 120/119.3 mm (height)
- Main rectangle dimensions: width 116/115.3 mm (with a tolerance of +/- 0.35 mm), height 114/113.3 mm
- Inner dimensions (main section): width 97.2/96.5 mm, height 77.2/76.5 mm, depth 4/6.5 mm
- Cutouts: ø3 mm and ø8.5 mm

![Base Sketch](./case_box4u/base.png)

### Lid

The lid of the case has the following specifications:
- Rounded corners (R6)
- Outer dimensions 122/121.5 mm (width) and 120/119.5 mm (height)
- Main rectangle dimensions: width 113/112.6 mm (with a tolerance of +/- 0.35 mm), height 111/110.6 mm
- Inner dimensions (main section): width 94.2/93.8 mm, height 74.2/73.8 mm

![Lid Sketch](./case_box4u/lid.png)

### Depth

The side view reveals the following specifications:

Lid:
- 15 mm depth including 3 mm thickness on top of the lid
- Total height of 55 mm
- Height without bottom and top plate thickness: 48 mm
- 40 mm including 4 mm bottom plate for the base case

![Side View](./case_box4u/side.png)

### Screw Detail

Cylinder Screws (M4 x 24 / 10 (DIN EN ISO 7045/))

![Detail of Screw](./case_box4u/screw.png)

## RAK Base Board Details

The board has the following specifications:
- a main rectangle of 69 (width) to 67 (height)
- 3 rectangular cutouts with 2x of 8mm * 14.50 and 1x 13 mm * 8mm
- 4x screw holes  (inner raidus of ø2.5 mm) / (outer radius ø5 mm)

![Board Sketch Top](./pcb_board/top.png)
![Board Sketch Bottom](./pcb_board/bottom.png)



## 3D Modelling in Auto Fusion 360

### Step 1 : Basement

We are starting with the sketch of the basement.
For that we configure the sizes like mentioned earlier above.
![Base Sketch](./case/base_sketch.png)
![Base Sketch Flat](./case/base_sketch_flat.png)

Then we extrude the needed areas for the sides and also the outer circles for the screws.
![Base Sketch Extrude](./case/base_sketch_extrude.png)


### Step 2 : Lid

Next we also configure the sizes for the lid like step 1.
![Lid Sketch](./case/lid_sketch.png)
![Lid Sketch Flat](./case/lid_sketch_flat.png)

We also extrude the specified areas.
![Lid Sketch Extrude](./case/lid_sketch_extrude.png)


### Step 3 : Board

Now continue with the rak board sketch and set the sizes as shown in the sketch.

![Board Sketch](./case/board_sketch.png)
![Board Sketch Flat](./case/board_sketch_flat.png)

We extrude the needed areas.
![Board Sketch Extrude](./case/board_sketch_extrude.png)


### Step 4 : Outline Basement

Lastly we set the sizes for the basement outline to fasten the board on the case, which is not possible with only the board , because of missing according holes. 

![Base Outline Sketch](./case/base_outline_sketch.png)
![Base Outline Sketch Flat](./case/base_outline_sketch_flat.png)

Then we are finishing it up with an extrude of the needed areas.
![Base Outline Sketch Extrude](./case/base_outline_sketch_extrude.png)


### Step 6 : Results
The Results should be as follows:

![View](./case/view1.png)
![Top View](./case/view_top.png)
![Front View](./case/view_front.png)
![Side View](./case/view_side.png)
![Endresult](./case/case.png)
