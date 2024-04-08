import unreal

lakeBP = unreal.EditorAssetLibrary.load_blueprint_class("/Game/BP/Landscape/ProceduralLakes/BaseLake")

def spawnLake(points=[]):
    loc = unreal.Vector(0., 0., 0.)
    rot = unreal.Rotator(0., 0., 0.)
    scale = unreal.Vector(1., 1., 1.)

    lake = unreal.WaterBodyLake(unreal.EditorLevelLibrary.spawn_actor_from_class(lakeBP, loc, rot))

    spline = lake.get_water_spline()
    
    if(len(points) < 3):
        return

    print("Before : ", [lake.get_water_spline().get_location_at_spline_input_key(i, unreal.SplineCoordinateSpace.WORLD) for i in range(spline.get_number_of_spline_points())])
    
    for i in range(len(points)):
        points[i] = unreal.Vector(points[i][0], points[i][1], points[i][2])
        
    spline.ResetSpline(points)

    # spline.k2_synchronize_and_broadcast_data_change()

    print("After : ", [lake.get_water_spline().get_location_at_spline_input_key(i, unreal.SplineCoordinateSpace.WORLD) for i in range(spline.get_number_of_spline_points())])