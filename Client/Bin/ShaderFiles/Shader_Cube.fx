
matrix		g_matWorld, g_matView, g_matProj;

texture		g_DiffuseTexture;

sampler DiffuseSampler = sampler_state
{
	texture = g_DiffuseTexture;
	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};

struct VS_IN
{
	float3		vPosition : POSITION;
	float3		vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	float4		vPosition : POSITION;
	float3		vTexUV : TEXCOORD0;
};

VS_OUT/*����*/ VS_MAIN(VS_IN In/*����*/)
{
	VS_OUT		Out = (VS_OUT)0;

	matrix		matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(float4(In.vPosition, 1.f), matWVP);
	Out.vTexUV = In.vTexUV;

	return Out;
}

// w������.(��������)

// ����Ʈ��ȯ.

// �����Ͷ�����.

struct PS_IN
{
	float4		vPosition : POSITION;
	float3		vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	float4		vColor : COLOR0;
};

PS_OUT PS_MAIN(PS_IN In/*�ȼ�*/)
{
	PS_OUT	Out = (PS_OUT)0;

	Out.vColor = texCUBE(DiffuseSampler, In.vTexUV);		

	return Out;
}





technique Default_Technique
{
	// ���� ǥ���ϰ����ϴ� ������Ǥ� ����.(���, ����ŧ��, �׸���, ������Ʈ, ��Ǻ�)
	pass Default_Rendering
	{
		CullMode = cw;
		ZWriteEnable = false;

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}

	//// ���ĺ��� + �ְ�
	//pass AlphaBlending
	//{
	//	VertexShader = ;
	//	PixelShader = ;
	//}
}