// pcm1808.c
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <sound/soc.h>

static const struct snd_soc_dapm_widget pcm1808_dapm_widgets[] = {
    SND_SOC_DAPM_INPUT("VINL"),
    SND_SOC_DAPM_INPUT("VINR"),
    SND_SOC_DAPM_ADC("ADC", NULL, SND_SOC_NOPM, 0, 0)
};

static const struct snd_soc_dapm_route pcm1808_dapm_routes[] = {
    { "Capture", NULL, "ADC" },
    { "ADC", NULL, "VINL" },
    { "ADC", NULL, "VINR" },
};

static struct snd_soc_dai_driver pcm1808_dai = {
    .name = "pcm1808-hifi",
    .capture = {
        .stream_name = "Capture",
        .channels_min = 2,
        .channels_max = 2,
        .rates = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_64000 | SNDRV_PCM_RATE_96000,
        .formats = SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE,
    },
};

static struct snd_soc_component_driver soc_component_dev_pcm1808 = {
    .dapm_widgets = pcm1808_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(pcm1808_dapm_widgets),
    .dapm_routes = pcm1808_dapm_routes,
    .num_dapm_routes = ARRAY_SIZE(pcm1808_dapm_routes),
};

static int pcm1808_probe(struct platform_device *pdev)
{
    return devm_snd_soc_register_component(&pdev->dev,
                                           &soc_component_dev_pcm1808,
                                           &pcm1808_dai, 1);
}

static const struct of_device_id pcm1808_of_match[] = {
    { .compatible = "ti,pcm1808", },
    {},
};
MODULE_DEVICE_TABLE(of, pcm1808_of_match);

static struct platform_driver pcm1808_driver = {
    .driver = {
        .name = "pcm1808-codec",
        .of_match_table = pcm1808_of_match,
    },
    .probe = pcm1808_probe,
};

module_platform_driver(pcm1808_driver);

MODULE_DESCRIPTION("ASoC PCM1808 ADC driver");
MODULE_AUTHOR("Florian Larysch <fl@n621.de>");
MODULE_LICENSE("GPL");
