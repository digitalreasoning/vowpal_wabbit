﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using VowpalWabbit.Serializer.Interfaces;

namespace VowpalWabbit.Serializer.Intermediate
{
    using VwHandle = IntPtr;

    public class Feature : IFeature
    {
        public string Namespace { get; set; }

        public char? FeatureGroup { get; set; }

        public string Name { get; set; }

        public bool Enumerize { get; set;  }
    }

    public sealed class Feature<T> : Feature, IFeature<T>
    {
        public T Value { get; set; }

        //internal void ToVW(VwHandle vw, VowpalWabbitInterface.FEATURE feature, uint namespaceHash)
        //{
        //    var value = this.Property.GetValue(this.Source);

        //    if (this.Converter != null)
        //    {
        //        var converter = Activator.CreateInstance(this.Converter) as IVowpalWabbitFeatureConverter;

        //        // refine a bit to know if it's taking care of sparse with name or dense
        //        value = converter.Convert(this.Property, value);
        //    }
        //    else if (this.Property.PropertyType.IsEnum)
        //    {
        //        value = string.Format("{0}_{1}", this.Property.Name, Enum.GetName(this.Property.PropertyType, value));
        //    }

        //    var valueStr = value as string;
        //    if (valueStr != null)
        //    {
        //        // TODO: what's the reason for vw global data structure being passed
        //        feature.weight_index = VowpalWabbitInterface.HashFeature(vw, valueStr, namespaceHash);
        //        feature.x = 1;
        //    }

        //    var dblValue = value as double?;
        //    if (dblValue != null)
        //    {
        //        feature.weight_index = VowpalWabbitInterface.HashFeature(vw, this.Property.Name, namespaceHash);
        //        feature.x = (float)dblValue;
        //    }
        //}
    }
}
