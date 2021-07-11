function [T] = Line_Nihe()
%ֱ�������������߹�ϵ

%��ߺ�����
H = [0.75 0.86 0.96 1.08 1.12 1.26 1.35 1.51 1.55 1.60 1.63 1.67 1.71 1.78 1.85];
W = [10 12 15 17 20 27 35 41 48 50 51 54 59 66 75];

%���
hmean = mean(H);
wmean = mean(W);
sumh2 = (H-hmean)*(H-hmean)';
sumhw = (W-wmean)*(H-hmean)';
a = sumhw/sumh2;
b = wmean-a*hmean;
T = [a b];

%��ͼ
%ԭ���ݵ�
scatter(H,W);
hold on;
%��Ϻ���
px = 0:1/100:3;
py = a*px+b;
plot(px,py);
end

