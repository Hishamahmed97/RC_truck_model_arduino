R = 50;
C = 1E-6;
model = "Project_RC_Circ.slx";
result = sim(model);
plot(result.logsout.get('vc').Values);